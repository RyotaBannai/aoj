{-# LANGUAGE MultiWayIf #-}
{-# LANGUAGE ViewPatterns #-}
{-# OPTIONS_GHC -Wno-incomplete-patterns #-}

module DoublyLinkedList where

import Common (cReadInputsTerm, readInputsTerm)
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as C
import Data.Foldable (toList)
import qualified Data.Sequence as S

-- * ALDS1_3_C

type Command a = (Int, a)

cInsert, cDelete, cDeleteFirst, cDeleteLast :: C.ByteString
cInsert = C.pack "insert"
cDelete = C.pack "delete"
cDeleteFirst = C.pack "deleteFirst"
cDeleteLast = C.pack "deleteLast"

insert :: S.Seq a -> a -> S.Seq a
insert (S.viewl -> S.EmptyL) v = S.empty S.|> v
insert n v = v S.<| n

delete :: (Eq a) => S.Seq a -> a -> S.Seq a
delete (S.viewl -> S.EmptyL) _ = S.empty
delete n v = case S.elemIndexL v n of -- 0 origin
  Nothing -> n
  Just i -> deleteAt n (i + 1)

deleteAt :: S.Seq a -> Int -> S.Seq a
deleteAt (S.viewl -> S.EmptyL) _ = S.empty
deleteAt n i = let (l, r) = S.splitAt i n in if S.null l then r else let (sx S.:> s) = S.viewr l in sx S.>< r -- 1 origin

deleteFirst :: S.Seq a -> S.Seq a
deleteFirst (S.viewl -> S.EmptyL) = S.empty
deleteFirst n = let (_ S.:< ss) = S.viewl n in ss

deleteLast :: S.Seq a -> S.Seq a
deleteLast (S.viewl -> S.EmptyL) = S.empty
deleteLast n = let (ss S.:> _) = S.viewr n in ss

run :: (Eq a) => S.Seq (Command a) -> S.Seq a -> S.Seq a
run (S.viewl -> S.EmptyL) s = s
run (S.viewl -> c@(name, v) S.:< cs) s = run cs $ eval c s

eval :: (Eq a) => Command a -> S.Seq a -> S.Seq a
eval (n, v) s =
  if
      | n == 1 -> insert s v
      | n == 2 -> delete s v
      | n == 3 -> deleteFirst s
      | n == 4 -> deleteLast s

nameToInt :: C.ByteString -> Int
nameToInt n =
  if
      | n == cInsert -> 1
      | n == cDelete -> 2
      | n == cDeleteFirst -> 3
      | n == cDeleteLast -> 4

toInt :: C.ByteString -> Int
toInt = (read :: String -> Int) . C.unpack

toTuple :: [C.ByteString] -> (Int, Int)
toTuple xs = let name = nameToInt . head $ xs in if length xs == 1 then (name, 0) else (name, toInt . last $ xs)

main :: IO ()
main = do
  _ <- getLine
  xs <- cReadInputsTerm
  putStrLn . unwords . map show . toList . uncurry run $ (S.fromList . map (toTuple . C.words) $ xs, S.empty)
