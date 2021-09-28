{-# LANGUAGE MultiWayIf #-}
{-# OPTIONS_GHC -Wno-incomplete-patterns #-}

module Dict where

import Common (cReadInputsTerm, readInputsTerm)
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as C
import Data.Foldable (toList)
import Data.HashMap.Strict (HashMap, (!))
import qualified Data.HashMap.Strict as M
import Data.List (foldl')
import Data.Maybe (fromJust)
import Data.Vector (Vector, (!))
import qualified Data.Vector as V

type Dict = HashMap Integer C.ByteString

type Command = Vector (C.ByteString, C.ByteString)

type Result = Vector C.ByteString

m :: Integer
m = 1046527

cInsert, cFind :: C.ByteString
cInsert = C.pack "insert"
cFind = C.pack "find"

charToInt :: Char -> Int
charToInt ch
  | ch == 'A' = 1
  | ch == 'C' = 2
  | ch == 'G' = 3
  | ch == 'T' = 4
  | otherwise = 0

getKey :: C.ByteString -> Integer
getKey str = fromIntegral sum
  where
    (sum, _, _) = C.foldl' f (0, 1, 0) str
    f (sum, p, i) ch = (sum + p * charToInt ch, p * 5, i + 1)

h1 :: Integer -> Integer
h1 = flip mod m

h2 :: Integer -> Integer
h2 = (+ 1) . flip mod (m -1)

h :: Integer -> Integer -> Integer
h k i = (h1 k + i * h2 k) `mod` m

isrt :: Dict -> C.ByteString -> (Bool, Dict)
isrt d str = if b then (True, d) else (False, M.insert (fromJust mh) str d)
  where
    (b, mh) = fnd d str 0

fnd :: Dict -> C.ByteString -> Integer -> (Bool, Maybe Integer)
fnd d cs i = case M.lookup h' d of
  Nothing -> (False, Just h')
  Just x -> if x == cs then (True, Nothing) else fnd d cs (i + 1)
  where
    k = getKey cs
    h' = h k i

run :: Command -> Result
run = snd . V.foldl' f (M.empty, V.empty)
  where
    f st@(d, re) (name, str) =
      if
          | cInsert == name ->
            let (b, d') = isrt d str
             in if b then st else (d', re)
          | cFind == name ->
            let yn = conv . fst $ fnd d str 0
             in (d, V.snoc re yn)
    conv b = C.pack (if b then "yes" else "no")

toTuple :: [C.ByteString] -> Command
toTuple = V.fromList . map ((\[f, s] -> (f, s)) . C.words)

main :: IO ()
main = (C.getLine >> cReadInputsTerm) >>= mapM_ C.putStrLn . toList . run . toTuple
