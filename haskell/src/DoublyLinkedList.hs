{-# LANGUAGE ViewPatterns #-}
{-# OPTIONS_GHC -Wno-incomplete-patterns #-}

module DoublyLinkedList where

import Common (readInputsTerm)
import Data.Foldable (toList)
import qualified Data.Sequence as S

-- * ALDS1_3_C

-- TODO: use bytestring to boost up speed

type Command a = (String, a)

opts :: [String]
opts = ["insert", "delete", "deleteFirst", "deleteLast"]

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
run (S.viewl -> c@(name, v) S.:< cs) s = let s' = if name `elem` opts then eval c s else s in run cs s'

eval :: (Eq a) => Command a -> S.Seq a -> S.Seq a
eval (name, v) s = case name of
  "insert" -> insert s v
  "delete" -> delete s v
  "deleteFirst" -> deleteFirst s
  "deleteLast" -> deleteLast s

toInt :: String -> Integer
toInt = read :: String -> Integer

toTuple :: [String] -> (String, Integer)
toTuple xs = if length xs == 1 then (head xs, 0) else (head xs, toInt . last $ xs)

main :: IO ()
main = do
  _ <- getLine
  xs <- readInputsTerm
  putStrLn $ unwords . map show . toList $ uncurry run (S.fromList . map (toTuple . words) $ xs, S.empty)
